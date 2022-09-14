# Run the Tests

## Text Tests
```sh
make text
```

## Unit Tests
```sh
make unit
```

## Approval Tests
```sh
make approvals
```

# Prerequisites

- `make` and a C++ compiler (like `gcc`) is installed on your system and is in the `PATH`
- The `CppUTest` framework is in the directory `CppUTest`

You can install it using:
```shell
./install-cpputest.sh
```

- for approval tests, you can run:
```shell
./get-approvals.sh
```