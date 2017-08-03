# generic_simulator
Generic simulator using C++ and inheritance

This project was started in 2002 as a simple demonstrator project for DEVS (Discrete Event System Specification) and was ended in 2007.

Later on it was enhanced to become a Generic Simulator like Simulink.

It has internal parser for expression and it could compute some expressions using also memory and vector positions (This is a modified version of the parser from Schild "C The Complete Reference" Copyright 1995 McGraw-Hill Cook Company International).

It contains also a statistical generator for repartitions (this was intended to be used as noise on the wires).

In DOCS there are some documentation and vector tests with diagrams.

Tests are done a long time ago and some after migration are no more working (some tests will create a loop this is because on the limitation of the model for dynamic flows and the dynamic UI is not working due also to model limitations)

FUTURE:

The project is stopped around 2007 and I have to migrate from VC 6.0 to Visual Studio 2016 in 2017.

This project is a dead end because for low memory management and easy connection I break the POO encapsulation and because I have used MFC Objects instead of stl objects. For the simple tests it was working but the problem arise on dynamical creation/duplicate of projects.

This project will be recreated in java as stand-alone or as part of the Chappy project.
