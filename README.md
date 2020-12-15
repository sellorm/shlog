shlog - The shell script log handler
================

<!--
DO NOT EDIT README.md DIRECTLY, IT IS AUTO-GENERATED FROM README.Rmd!!
-->

You write shell scripts, right?

And you’re always knocking some sort of rough logging solution together
for each script.

We know, because we were exactly the same! And that’s why we created
`shlog`, an easy to use, small, fast tool for printing consistent log
messages directly to the terminal from your script

Opinionated by design, `shlog` has the bare minimum of options to ensure
you’re productive with it right from the outset.

## Installing shlog

Installation must currently be performed manually. Compile the sources
from the [GitHub repo](https://github.com/sellorm/shlog) and copy the
`shlog` binary somewhere on your `$PATH`.

## Using shlog

The `shlog` command requires two arguments. A loglevel for the given
message and the mesaage itself;

``` bash
./shlog info "This is an information message!"
```

    ## 2020-12-15 23:33:00 [  INFO ] This is an information message!

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

    ## 2020-12-15 23:33:00 [ ERROR ] This is an error message

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

    ## 2020-12-15 23:33:00 [ DEBUG ] This is a debug message

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

## Examples

Only the first message is printed:

``` bash
export LOGLEVEL=INFO
./shlog info "This is an info message"
./shlog DEBUG "This is a debug message"
```

    ## 2020-12-15 23:33:00 [  INFO ] This is an info message

Both messages are printed:

``` bash
export LOGLEVEL=debug
./shlog info "This is an info message"
./shlog DEBUG "This is a debug message"
```

    ## 2020-12-15 23:33:00 [  INFO ] This is an info message
    ## 2020-12-15 23:33:00 [ DEBUG ] This is a debug message

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

    ## 2020-12-15 23:33:00 [ FATAL ] This is a FATAL message
    ## 2020-12-15 23:33:00 [ ERROR ] This is an ERROR message
    ## 2020-12-15 23:33:00 [  WARN ] This is a WARN message

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

## License

This work is release under the [MIT
License](https://github.com/sellorm/shlog/blob/main/LICENSE) by Mark
Sellors.
