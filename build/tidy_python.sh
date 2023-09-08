#!/bin/bash
#
# Adds default flags to all the templates and sorts them so it is easier to
# see what is missing or needs added.
#
# Use "do" as the first arg if the output looks sane.
#

PRE=$(mktemp) || exit 1
PAYLOAD=$(mktemp) || exit 1
POST=$(mktemp) || exit 1
OUT=$(mktemp) || exit 1

for i in \
  amulets \
  armor \
  boots \
  buffs \
  cloaks \
  containers \
  debuffs \
  doors \
  dungeon \
  effects \
  food \
  fungus \
  gauntlets \
  internal \
  items \
  keys \
  lasers \
  mobs \
  monsters \
  player \
  potions \
  projectiles \
  rings \
  shield \
  skills \
  spells \
  staffs \
  traps \
  totem \
  treasure \
  weapons
do
  cp .flake8 $i/
  git add $i/.flake8
done

for IN in \
  amulets/*py \
  armor/*py \
  boots/*py \
  buffs/*py \
  cloaks/*py \
  containers/*py \
  debuffs/*py \
  doors/*py \
  dungeon/*py \
  effects/*py \
  food/*py \
  fungus/*py \
  gauntlets/*py \
  internal/*py \
  items/*py \
  keys/*py \
  lasers/*py \
  mobs/*py \
  monsters/*py \
  player/*py \
  potions/*py \
  projectiles/*py \
  rings/*py \
  shield/*py \
  skills/*py \
  spells/*py \
  staffs/*py \
  traps/*py \
  totem/*py \
  treasure/*py \
  weapons/*py
do
    echo Tidying $IN...

    grep -q is_monst_pack $IN
    if [ $? -eq 0 ]; then
        continue
    fi

    sed '1,/begin sort marker/!d' $IN > $PRE
    sed '/begin sort marker/,/end sort marker/!d' $IN | tail -n +1 - | grep -v "sort marker" | sort > $PAYLOAD
    sed '/end sort marker/,$!d' $IN | tail -n +1 - > $POST

    sort $PAYLOAD | uniq > $PAYLOAD.tmp
    mv $PAYLOAD.tmp $PAYLOAD

    cat $PRE $PAYLOAD $POST > $OUT

    diff $OUT $IN

    if [ "$1" = "do" ]; then
        mv $OUT $IN
    fi
done
