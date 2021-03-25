#!/usr/bin/env python3

import collections
import pathlib
import math
import re
import os

files = collections.defaultdict(list)
root = pathlib.Path(".")

file_count = 0
ram_files = 10

for filepath in root.rglob(r'data/gfx/*.tga'):
    files[filepath.parent].append(filepath.name)
    file_count += 1

for ram_file in range(ram_files):
    with open("src/ramdisk_data_{}.S".format(ram_file), "w") as myfile:
        myfile.write("// Ramdisk data for files that due to licensing cannot be exposed\n\n")

count = 0
for record_number, (folder, filenames) in enumerate(sorted(files.items())):
    for filename in enumerate(filenames):
        ram_file = count % ram_files 
        count += 1

        rec, orig_filename = filename
        c_filename = orig_filename
        c_filename = re.sub("-", "_", c_filename)
        c_filename = re.sub("\.", "_", c_filename)
        rel_path_filename = os.path.join(folder, orig_filename)

        with open("src/ramdisk_data_{}.S".format(ram_file), "a") as myfile:
            myfile.write(".globl {}_start_\n".format(c_filename))
            myfile.write("{}_start_:\n".format(c_filename))
            myfile.write(".incbin \"../{}\"\n".format(rel_path_filename))
            myfile.write(".globl {}_end_\n".format(c_filename))
            myfile.write("{}_end_:\n".format(c_filename))
            myfile.write("\n")

with open("src/ramdisk_data.cpp".format(ram_file), "w") as myfile:
    myfile.write("#include \"my_ramdisk.h\"")
    myfile.write("\n")
    myfile.write("\n")
    myfile.write("void ramdisk_init (void)\n")
    myfile.write("{\n")

    count = 0
    for record_number, (folder, filenames) in enumerate(sorted(files.items())):
        for filename in enumerate(filenames):
            ram_file = count % ram_files 
            count += 1

            rec, c_filename = filename
            c_filename = re.sub("-", "_", c_filename)
            c_filename = re.sub("\.", "_", c_filename)
            rel_path_filename = os.path.join(folder, c_filename)

            myfile.write("    {\n")
            myfile.write("        extern unsigned char *data_{}_data_start_ asm(\"data_{}_data_start_\");\n".format(c_filename, c_filename))
            myfile.write("        extern unsigned char *data_{}_data_end_ asm(\"data_{}_data_end_\");\n".format(c_filename, c_filename))
            myfile.write("        static const unsigned char *const start = (const unsigned char *const) (char*)&data_{}_data_start_;\n".format(c_filename, c_filename))
            myfile.write("        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_{}_data_end_;\n".format(c_filename, c_filename))
            myfile.write("        ramdisk_t r;\n")
            myfile.write("        r.data = start;\n")
            myfile.write("        r.len = end - start;\n")
            myfile.write("        ramdisk_data[\"{}\"] = r;\n".format(rel_path_filename))
            myfile.write("    }\n")
            myfile.write("\n")

    myfile.write("}\n")

