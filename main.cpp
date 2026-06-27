#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int getMaxBrightness(){

  ifstream Filename("/sys/class/backlight/intel_backlight/max_brightness");
  
  if (!Filename.is_open()) {
    cout << "Error opening file...";
    return 1;
  }

  string maxBrightness;
  getline(Filename, maxBrightness);

  int maxBrightnessInteger = stoi(maxBrightness);

  Filename.close();

  return maxBrightnessInteger;
}

int getBrightness(){
  
  ifstream Filename("/sys/class/backlight/intel_backlight/brightness");
  
  if (!Filename.is_open()) {

    cout << "Error opening file...";
    return 1;
  }

  string brightness;
  getline(Filename, brightness);
  
  int brightnessInteger = stoi(brightness);
  
  Filename.close();

  return brightnessInteger;
}

int increaseBrightness(int value){

  int newBrightness, maxBrightness;
  ofstream Filename;

  newBrightness = getBrightness();
  newBrightness = newBrightness + value;

  maxBrightness = getMaxBrightness();

  if(newBrightness > maxBrightness){
    newBrightness = maxBrightness;
    cout << "Brightness is at maximum" << endl;
  }
  else{
    cout << "Brightness increased by " << value << endl;
  }

  Filename.open("/sys/class/backlight/intel_backlight/brightness", ofstream::trunc);
  
  if (!Filename.is_open()) {

    cout << "Error opening file... File not open.";
    return 1;
  }

  else if(Filename.fail()){
    cout << "Error opening file... Permission error.";
    return 1;
  }
  
  Filename << newBrightness;
  Filename.close();

  return newBrightness;
}

int decreaseBrightness(int value){

  int newBrightness, maxBrightness;

  newBrightness = getBrightness();
  newBrightness = newBrightness - value;

  maxBrightness = getMaxBrightness();

  if(newBrightness <= 0){
    newBrightness = 100;
    cout << "Brightness can't go below 0" << endl;
  }

  else{
    cout << "Brightness decreased by " << value << endl;
  }

  ofstream Filename;
  Filename.open("/sys/class/backlight/intel_backlight/brightness", ofstream::trunc);
  
  if (!Filename.is_open()) {
    cout << "Error opening file... File not open.";
    return 1;
  }

  else if(Filename.fail()){
    cout << "Error opening file... Permission error.";
    return 1;
  }
  
  Filename << newBrightness;
  Filename.close();
  
  return newBrightness;
}

int main(int argc, char* argv[]){
    
    if(argc < 2){
      cout << "Invalid operation. Usage: ./dimmer [up/down] [value]" << endl;
      return 1;
    }

    string action = argv[1];
    int value = 5000; 

    if(argc >= 3) {
        value = stoi(argv[2]); 
    }
            
    if (action == "up"){
        increaseBrightness(value); 
    }
    
    else if (action == "down"){
        decreaseBrightness(value);
    }

    else{
        cout << "Invalid operation: use 'up' or 'down'" << endl;
        return 1;
    }

    return 0;
}