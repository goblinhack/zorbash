#
# common shell utilities
#

ESC=""

DULL=0
BRIGHT=1

FG_BLACK=30
FG_RED=31
FG_GREEN=32
FG_YELLOW=33
FG_BLUE=34
FG_MAGENTA=35
FG_CYAN=36
FG_WHITE=37

FG_NULL=00

BG_BLACK=40
BG_RED=41
BG_GREEN=42
BG_YELLOW=43
BG_BLUE=44
BG_MAGENTA=45
BG_CYAN=46
BG_WHITE=47

BG_NULL=00

ESC="["
NORMAL="${ESC}m"
RESET="${ESC}${DULL};${FG_WHITE};${BG_NULL}m"

# DULL TEXT
BLACK="${ESC}${DULL};${FG_BLACK}m"
RED="${ESC}${DULL};${FG_RED}m"
GREEN="${ESC}${DULL};${FG_GREEN}m"
YELLOW="${ESC}${DULL};${FG_YELLOW}m"
BLUE="${ESC}${DULL};${FG_BLUE}m"
MAGENTA="${ESC}${DULL};${FG_MAGENTA}m"
CYAN="${ESC}${DULL};${FG_CYAN}m"
WHITE="${ESC}${DULL};${FG_WHITE}m"

ON_BLACK="${ESC}${DULL};${BG_BLACK}m"
ON_RED="${ESC}${DULL};${BG_RED}m"
ON_GREEN="${ESC}${DULL};${BG_GREEN}m"
ON_YELLOW="${ESC}${DULL};${BG_YELLOW}m"
ON_BLUE="${ESC}${DULL};${BG_BLUE}m"
ON_MAGENTA="${ESC}${DULL};${BG_MAGENTA}m"
ON_CYAN="${ESC}${DULL};${BG_CYAN}m"
ON_WHITE="${ESC}${DULL};${BG_WHITE}m"

# BRIGHT TEXT
BRIGHT_BLACK="${ESC}${BRIGHT};${FG_BLACK}m"
BRIGHT_RED="${ESC}${BRIGHT};${FG_RED}m"
BRIGHT_GREEN="${ESC}${BRIGHT};${FG_GREEN}m"
BRIGHT_YELLOW="${ESC}${BRIGHT};${FG_YELLOW}m"
BRIGHT_BLUE="${ESC}${BRIGHT};${FG_BLUE}m"
BRIGHT_MAGENTA="${ESC}${BRIGHT};${FG_MAGENTA}m"
BRIGHT_CYAN="${ESC}${BRIGHT};${FG_CYAN}m"
BRIGHT_WHITE="${ESC}${BRIGHT};${FG_WHITE}m"

setenv() {
    eval "$1='$2'"; export $1;
}

log() {
    echo "${MAGENTA}$*${RESET}"
}

log_info() {
    echo "zorbash: ${GREEN}$*${RESET}"
}

log_echo() {
    echo "zorbash: $*"
}

log_err() {
    echo "zorbash: ${RED}ERROR: $*${RESET}"
}

log_warn() {
    echo "zorbash: ${CYAN}WARN: $*${RESET}"
}

log_die() {
    echo "zorbash: ${RED}FATAL ERROR: $*${RESET}"
    echo "Mail goblinhack@gmail.com for help"
    exit 1
}

run() {
    echo "  $*"
    $*
}
