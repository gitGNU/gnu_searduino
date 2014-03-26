# Testing Jearduino

All actions below shall be performed with jearduino started in the
following different ways.


# Starting Jearduino

 * No arguments:  
      jearduino 

 * Board argument: 
      jearduino --board Uno

 * Start argument: 
      jearduino --start

 * Arduino Code argument: 
      jearduino --arduino-code <path>/example/digpins/digpins.so

 * Arduino Code and board argument: 
      jearduino --arduino-code <path>/example/digpins/digpins.so --board Uno

 * Arduino Code and misc argument: 
      jearduino --arduino-code <path>/example/digpins/digpins.so --board Uno --start

 * Searduino Project argument: 
      jearduino --arduino-code <path>/searduino/Blink/

 * Searduino Project and Board arguments: 
      jearduino --arduino-code <path>/searduino/Blink/ --board Uno

 * Searduino Project and misc arguments: 
      jearduino --arduino-code <path>/searduino/Blink/ --board Uno --start

# Test cases

## Check version

* Choose About
* Make sure that the version number is correct


## Set board

* Choose Boards->Uno
* Make sure the pins are correctly layed out


* Choose Boards->Leaonard
* Make sure the pins are correctly layed out

