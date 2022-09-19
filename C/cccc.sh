$CCCC GildedRose.c &> /dev/null
yq -p=xml '.[].[].member_function.[] | [.lines_of_code.+value,.McCabes_cyclomatic_complexity.+value,.name] | join(", ")' .cccc/anonymous.xml
