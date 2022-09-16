- code coverage is interesting!
- idea - `approvals.verify(coverageReport)`!
- conclusion - one big smell is the reuse of `item->quality` through the `update` calculations;
  it's a problem both 1. mentally and 2. for refactoring;
  I wonder if there's a known smell for this phenomenon
- idea (at least as an exercise) - two passes on the 'items': 1. first pass - assign an 'updater' to the item 2. second
  pass - call the `update` function
- do the actual kata
- why does clang not work in vscode?
- should some of this be part of approvals?
- combination approvals
- idea - 2D table iso one line per item: rows are days, columns are items
- ~~updaters should be initialized *once*, there's no need for them to be determined dynamically~~
- ~~move updaters to own files~~
- ~~have a separate make target for the approval tests~~
