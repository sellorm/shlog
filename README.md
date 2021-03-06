shlog - The shell script log handler
================

<!--
DO NOT EDIT README.md DIRECTLY, IT IS AUTO-GENERATED FROM README.Rmd!!
-->

You write shell scripts, right?

And you’re always knocking together some sort of rough logging solution
for each script.

We know, because we were exactly the same! And that’s why we created
`shlog`, an easy to use, small, fast tool for printing consistent log
messages directly to the terminal from your script.

Opinionated by design, `shlog` has the bare minimum of options to ensure
you’re productive with it right from the outset.

## Installing shlog

### Version 0.0.1:

-   [Ubuntu
    20.04](https://github.com/sellorm/shlog/releases/download/v0.0.1/shlog_0.0.1-3_ubuntu2004_amd64.deb)
-   [Ubuntu
    18.04](https://github.com/sellorm/shlog/releases/download/v0.0.1/shlog_0.0.1-3_ubuntu1804_amd64.deb)

## Using shlog

The `shlog` command requires two arguments. A loglevel for the given
message and the mesaage itself;

``` bash
./shlog info "This is an information message!"
```

    ## 2020-12-18 09:33:35 [  INFO ] This is an information message!

The available loglevels are (in highest priority first order):

-   FATAL
-   ERROR
-   WARN
-   INFO
-   DEBUG
-   TRACE

These can be specified in either upper or lower case.

``` bash
./shlog ERROR "This is an error message"
```

    ## 2020-12-18 09:33:35 [ ERROR ] This is an error message

By default the loglevel is set to INFO.

-   FATAL
-   ERROR
-   WARN
-   INFO &lt;–
-   DEBUG
-   TRACE

This means that you will only see messages that have a priority of INFO
or higher.

So, by default, the following command will not print anything:

``` bash
./shlog DEBUG "This is a debug message"
```

You change the loglevel by setting the `LOGLEVEL` environment variable
either in your script or the parent environment.

So the following will print:

``` bash
export LOGLEVEL=DEBUG
./shlog DEBUG "This is a debug message"
```

    ## 2020-12-18 09:33:35 [ DEBUG ] This is a debug message

This is because we used the environment variable to tell `shlog` the
lowest type of log message we would like to see.

-   FATAL
-   ERROR
-   WARN
-   INFO
-   DEBUG &lt;–
-   TRACE

`shlog` also supports two special environment variables, `ALL` and
`OFF`, which print all messages or turns all messages off respectively.

## Newline delimited JSON

Perhaps your shell script project is part of something larger and you’d
prefer structured log output. Don’t worry, `shlog` has your back.

Set the environment variable `SHLOG_JSON` to `true` and logs will be
output as newline delimited JSON instead of standard plain text.

``` bash
export SHLOG_JSON=true
./shlog INFO "This is an info message"
```

    ## {"date":"2020-12-18","time":"09:33:35","level":"INFO","message":"This is an info message"}

## Examples

Only the first message is printed:

``` bash
export LOGLEVEL=INFO
./shlog info "This is an info message"
./shlog DEBUG "This is a debug message"
```

    ## 2020-12-18 09:33:35 [  INFO ] This is an info message

Both messages are printed:

``` bash
export LOGLEVEL=debug
./shlog info "This is an info message"
./shlog DEBUG "This is a debug message"
```

    ## 2020-12-18 09:33:35 [  INFO ] This is an info message
    ## 2020-12-18 09:33:35 [ DEBUG ] This is a debug message

Everything from `WARN` and above is printed:

``` bash
export LOGLEVEL=WARN
./shlog FATAL "This is a FATAL message"
./shlog ERROR "This is an ERROR message"
./shlog WARN "This is a WARN message"
./shlog INFO "This is an INFO message"
./shlog DEBUG "This is a DEBUG message"
./shlog TRACE "This is a TRACE message"
```

    ## 2020-12-18 09:33:35 [ FATAL ] This is a FATAL message
    ## 2020-12-18 09:33:35 [ ERROR ] This is an ERROR message
    ## 2020-12-18 09:33:35 [  WARN ] This is a WARN message

Only two out of these three messages are at loglevel or above and all
messages use JSON output:

``` bash
export LOGLEVEL=INFO
export SHLOG_JSON=true
./shlog info "This is an info message"
./shlog DEBUG "This is a debug message"
./shlog error "This is an error message"
```

    ## {"date":"2020-12-18","time":"09:33:35","level":"INFO","message":"This is an info message"}
    ## {"date":"2020-12-18","time":"09:33:35","level":"ERROR","message":"This is an error message"}

## Working on shlog

### Building shlog

Clone the git repo:

    git clone git@github.com:sellorm/shlog.git

Then cd into the shlog directory and run `make`:

    cd shlog
    make

### Testing shlog

To run the test script:

    make test

This script runs every combination of log message configuration and
loglevel and will output all appropriate messages in the terminal, like
this:

    LOGLEVEL is ERROR
    2020-12-15 23:28:20 [ ERROR ] this message is error
    2020-12-15 23:28:20 [ ERROR ] this message is ERROR
    2020-12-15 23:28:20 [ FATAL ] this message is fatal
    2020-12-15 23:28:20 [ FATAL ] this message is FATAL
    LOGLEVEL is fatal
    2020-12-15 23:28:20 [ FATAL ] this message is fatal
    2020-12-15 23:28:20 [ FATAL ] this message is FATAL

It will then repeat all the tests with `SHLOG_JSON=true` to output
newline delimited JSON, like this:

    LOGLEVEL is WARN
    {"date":"2020-12-17","time":"11:04:08","level":"WARN","message":"this message is warn"}
    {"date":"2020-12-17","time":"11:04:08","level":"WARN","message":"this message is WARN"}
    {"date":"2020-12-17","time":"11:04:08","level":"ERROR","message":"this message is error"}
    {"date":"2020-12-17","time":"11:04:08","level":"ERROR","message":"this message is ERROR"}
    {"date":"2020-12-17","time":"11:04:08","level":"FATAL","message":"this message is fatal"}
    {"date":"2020-12-17","time":"11:04:08","level":"FATAL","message":"this message is FATAL"}

## License

This work is released under the [MIT
License](https://github.com/sellorm/shlog/blob/main/LICENSE) by [Mark
Sellors](https://blog.sellorm.com).
