#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  BreachType brchType = NORMAL;
  if(value < lowerLimit) {
    brchType = TOO_LOW;
  }
  else if(value > upperLimit) {
    brchType = TOO_HIGH;
  }
  return brchType;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimitarray[3] = {35,45,40};  // Upper limit in coolingtype order (PASSIVE_COOLING, HI_ACTIVE_COOLING, MED_ACTIVE_COOLING)

  return inferBreach(temperatureInC, lowerLimit, upperLimitarray [coolingType]);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  // switch(breachType) {
  //   case TOO_LOW:
  //     printf("To: %s\n", recepient);
  //     printf("Hi, the temperature is too low\n");
  //     break;
  //   case TOO_HIGH:
  //     printf("To: %s\n", recepient);
  //     printf("Hi, the temperature is too high\n");
  //     break;
  //   case NORMAL:
  //     break;
  // }
  if (breachType == TOO_LOW){
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too low\n");
  }
  else if (breachType == TOO_HIGH){
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too high\n");
  }
}
