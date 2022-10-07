echo "count\tline\tcode"
ack -o '[\d#]+:\W+\d+:[^\"]{0,14}' GildedRose.c.gcov |
sed 's/[^\"]*/"&"/' |
sed -E 's/#+/0/' |
jq -s 'map(split(":") |
    {
      count:.[0] | tonumber,
      line:.[1] | tonumber,
      code:.[2]
    }
  ) |
  sort_by(.line) | reverse |
  sort_by(.count) | reverse |
  map(select(.count == 0)) + map(select(.count > 0)) |
  .[0:4] |
  map([.count,.line,.code] | join("\t"))' |
yq '.[]'
