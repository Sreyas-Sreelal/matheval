#  matheval

[![Build Status](https://travis-ci.com/Sreyas-Sreelal/matheval.svg?branch=master)](https://travis-ci.com/Sreyas-Sreelal/matheval) [![GitHub issues](https://img.shields.io/github/issues/Sreyas-Sreelal/matheval.svg)]() [![GitHub pull requests](https://img.shields.io/github/issues-pr-raw/sreyas-sreelal/matheval.svg)]() [![GitHub pull license](https://img.shields.io/github/license/sreyas-sreelal/matheval.svg)]()

This is a simple library for evaluating mathematical expressions given as string literals.

###  Installation

If you are using sampctl just use

`sampctl package install Sreyas-Sreelal/matheval`

Otherwise just clone the repository

`git clone https://www.github.com/sreyas-sreelal/matheval.git`

and add matheval.inc to your pawno/includes folder

###  Usage

There is only one function

`MathEval(expression[])`

####  parameters

* expression[] - mathmatical expression in string literal

####  returns

* NaN if failed
* if success,value in floating point

For example :

```pawn
MathEval('(1+3)^(32/3)-1');
```

###  Testing

To run the tests:

`sampctl package run`

###  Dependencies

* SA-MP 0.3.7 by SA-MP team - https://www.sa-mp.com/download.php

* sampctl by SouthClaws (optional but recommended) - https://github.com/Southclaws/sampctl