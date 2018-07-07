#!/usr/bin/perl

my $filelist = $ARGV[0];

my @files = (split(/\n/, `cat $filelist`));

# open(OUT, ">", "src/ramdisk_files.c");
# 
# printf OUT "#include <stdint.h>\n";
# printf OUT "#include \"ramdisk.h\"\n";
# printf OUT "\n";
# 
# print OUT "\nramdisk_t ramdisk_files[] = {\n";
# 
# foreach $f (@files) {
# 
#     my $file = "$f";
# 
#     my $struct = $f;
#     $struct =~ s/\//_/g;
#     $struct =~ s/\./_/g;
# 
#     my $size = $sizes{$f};
#     my $orig_size = $orig_sizes{$f};
# 
#     print "  $f\n";
# 
#     print OUT "    {\n";
#     print OUT "        \"$f\",\n";
#     print OUT "        0,\n";
#     print OUT "        0,\n";
#     print OUT "        0,\n";
#     print OUT "    },\n";
# }
# 
# print OUT "    {0},\n";
# print OUT "};\n";
# 
# close(OUT);

my $PWD = `pwd`;

chomp($PWD);

my $cnt = 1;
my $max_cnt = 10;

foreach $f (@files) {

    my $file = "$f";

    my $struct = $f;
    $struct =~ s/\//_/g;
    $struct =~ s/\./_/g;
    $struct =~ s/\-/_/g;

    my $size = -s $f;

    if (!defined $file_size{$cnt}) {
        $file_size{$cnt} = $size;
    } else {
        my $looped = 1;

        while ($file_size{$cnt} + $size > 1000 * 1000 * 100) {
            $cnt++;
            if ($cnt >= $max_cnt) {
                $cnt = 1;
                if (!$looped) {
                    break;
                }
                $looped++;
            }
        }

        $file_size{$cnt} += $size
    }

    $file_deps{$cnt} .= "../" . $file . " ";

    if (!defined $done{$cnt}) {
        print "Generating src/asm/ramdisk_" . $cnt . ".S\n";

        open(OUT, ">", "src/asm/ramdisk_" . $cnt . ".S");

        $done{$cnt} = 1;
    } else {
        open(OUT, ">>", "src/asm/ramdisk_" . $cnt . ".S");
    }

    $cnt++;
    if ($cnt >= $max_cnt) {
        $cnt = 1;
    }

    print OUT ".globl ${struct}_start_\n";
    print OUT "${struct}_start_:\n";

    #
    # MingW didn't seem to like full paths
    #
    if ( `uname` =~ /.*MING.*/) {
        print OUT ".incbin \"../$file\"\n";
    } elsif ( `uname` =~ /.*MSYS.*/) {
        print OUT ".incbin \"../$file\"\n";
    } else {
        print OUT ".incbin \"$PWD/$file\"\n";
    }

    print OUT ".globl ${struct}_end_\n";
    print OUT "${struct}_end_:\n";
    print OUT "\n";

    close(OUT);
}

for ($cnt = 1; $cnt < $max_cnt; $cnt++) {
    print "Created src/asm/ramdisk_" . $cnt . ".S (size " . int ($file_size{$cnt}  / (1024 * 1024)) . "Mb)\n";
}

close(OUT);

open(OUT, ">", "src/Makefile.ramdisk");

for ($cnt = 1; $cnt < $max_cnt; $cnt++) {

    my $struct = $f;
    $struct =~ s/\//_/g;
    $struct =~ s/\./_/g;
    $struct =~ s/\-/_/g;

    my $size = $sizes{$f};
    my $orig_size = $orig_sizes{$f};

    print OUT ".o/ramdisk_" . $cnt . ".o: ";
    print OUT "asm/ramdisk_" . $cnt . ".S ";

    my $file = $file_deps{$cnt};

    print OUT "$file\n";
    print OUT "\tgcc -c ";
    print OUT "asm/ramdisk_" . $cnt . ".S ";
    print OUT "-o ";
    print OUT ".o/ramdisk_" . $cnt . ".o\n";
    print OUT "\n";
}

close(OUT);

open(OUT, ">", "src/Makefile.ramdisk.deps");

print OUT "RAMDISK_OBJ=";

for ($cnt = 1; $cnt < $max_cnt; $cnt++) {

    my $file = "$f";

    my $struct = $f;
    $struct =~ s/\//_/g;
    $struct =~ s/\./_/g;
    $struct =~ s/\-/_/g;

    print OUT ".o/ramdisk_" . $cnt . ".o ";
}

#print OUT "\n\nall: \$(RAMDISK_OBJ)\n";

close(OUT);

open(OUT, ">", "src/ramdisk_data.c");

printf OUT "#include <stdint.h>\n";
printf OUT "#include \"ramdisk.h\"\n";
printf OUT "\n";

foreach $f (@files) {

    my $file = "$f";

    my $struct = $f;
    $struct =~ s/\//_/g;
    $struct =~ s/\./_/g;
    $struct =~ s/\-/_/g;

    my $size = $sizes{$f};
    my $orig_size = $orig_sizes{$f};

    printf OUT "extern unsigned char *${struct}_start_ asm(\"${struct}_start_\");\n";
    printf OUT "extern unsigned char *${struct}_end_ asm(\"${struct}_end_\");\n";
    printf OUT "static const unsigned char *const ${struct}_start =\n    (const unsigned char *const) (char*)\&${struct}_start_;\n";
    printf OUT "static const unsigned char *const ${struct}_end   =\n    (const unsigned char *const) (char*)\&${struct}_end_;\n";
    print OUT "\n";
}

printf OUT "ramdisk_t ramdisk_data[] = {\n";

foreach $f (@files) {

    my $file = "$f";

    my $struct = $f;
    $struct =~ s/\//_/g;
    $struct =~ s/\./_/g;
    $struct =~ s/\-/_/g;

    my $filesize = -s "$file";
    my $size = $filesize;
    my $orig_size = $filesize;

    printf OUT "{\n";
        printf OUT "    \/* filename *\/ \"$file\",\n";
    printf OUT "},\n";
}

printf OUT "    {0},\n";
printf OUT "};\n";
printf OUT "\n";
printf OUT "void ramdisk_init (void)\n";
printf OUT "{\n";

my $cnt = 0;
foreach $f (@files) {

    my $file = "$f";

    my $struct = $f;
    $struct =~ s/\//_/g;
    $struct =~ s/\./_/g;
    $struct =~ s/\-/_/g;

    printf OUT "    ramdisk_data[%d].data = ${struct}_start;\n", $cnt;
    printf OUT "    ramdisk_data[%d].len = (int32_t) (${struct}_end - ${struct}_start);\n", $cnt;
    $cnt++;
}

printf OUT "}\n";

close(OUT);
