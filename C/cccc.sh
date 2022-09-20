rm -rf .cccc
$CCCC GildedRose.c &> /dev/null
echo "loc\tcmplx.\tmethod"
yq -p=xml -o=json '.[].[].member_function |
  select(. != ~) |
  map({"n":.name, "l":.lines_of_code.+value, "c":.McCabes_cyclomatic_complexity.+value}) |
  sort_by(.l)|
  reverse' .cccc/anonymous.xml |
jq "map({\"c\":.c | tonumber, \"l\":.l | tonumber, \"n\":.n | split(\"(\")[0]}) |
  sort_by(.c) | sort_by(.l) | reverse | map([.l,.c,.n] | join(\"\t\"))" |
yq '.[]'
