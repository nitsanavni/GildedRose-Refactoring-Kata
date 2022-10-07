rm -rf .cccc
$CCCC GildedRose.c &> /dev/null
echo "loc\tcmplx.\tmethod"
yq -p=xml -o=json .cccc/anonymous.xml | \
jq '.CCCC_Project.procedural_detail.member_function |
  map({
    n:.name | split("(")[0],
    l:.lines_of_code."+value" | tonumber,
    c:.McCabes_cyclomatic_complexity."+value" | tonumber}) |
  sort_by(.c) | sort_by(.l) | reverse | .[0:5] |
  map([.l,.c,.n] | join("\t"))' |
yq '.[]'
