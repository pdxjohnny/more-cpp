#!/bin/bash

OLD=$1
NEW=$2
OLD_UPPER=$(echo "${OLD}" | tr '[:lower:]' '[:upper:]')
NEW_UPPER=$(echo "${NEW}" | tr '[:lower:]' '[:upper:]')

for i in $(find . -type f | grep "${OLD}"); do
    j=$(echo "$i" | sed "s/${OLD}/${NEW}/g");
    mv $i $j;
done
sed -i "s/${OLD}/${NEW}/g" $(find . -type f)
sed -i "s/${OLD_UPPER}/${NEW_UPPER}/g" $(find . -type f)
