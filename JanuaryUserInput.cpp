// VEX V5 C++ Project with Competition Template
#include "vex.h"
using namespace vex;

//#region config_globals
vex::brain      Brain;
vex::motor      rear_right(vex::PORT1, vex::gearSetting::ratio18_1, true);
vex::motor      arm(vex::PORT3, vex::gearSetting::ratio36_1, false);
vex::motor      rear_left(vex::PORT10, vex::gearSetting::ratio18_1, false);
vex::motor      front_right(vex::PORT11, vex::gearSetting::ratio18_1, true);
vex::motor      front_left(vex::PORT20, vex::gearSetting::ratio18_1, false);
vex::bumper     brake(Brain.ThreeWirePort.A);
vex::controller controller(vex::controllerType::primary);
//#endregion config_globals
 int right_turn_var = 0;
        int left_turn_var = 0;
        int drive_type = 0;
        int speed_left = 0;
        int speed_right = 0;
        int buttonpressed = 0;
        
bool error = false;
// Creates a competition object that allows access to Competition methods.
vex::competition Competition;

void pre_auton() {
    // All activities that occur before competition start
    // Example: setting initial positions

    if brake != 1 {
        front_left.setStopping(brake);
        front_right.setStopping(brake);
        rear_right.setStopping(brake);
        rear_left.setStopping(brake);
    }
        
    

}

void autonomous() {
    // Place autonomous code here

}

void drivercontrol() {
    // Place drive control code here, inside the loop
    while (true) {
        // This is the main loop for the driver control
        // Each time through the loop you should update motor
        // movements based on input from the controller.
        
         //screen
         Brain.Screen.setPenColor(vex::color::white);
        Brain.Screen.setFillColor(vex::color::black);
        Brain.Screen.drawRectangle(0,0, 480, 240);
        //button1
         Brain.Screen.setPenColor(vex::color::white);
        Brain.Screen.setFillColor(vex::color::red);
        Brain.Screen.drawRectangle(60, 20, 200, 100);
        //button2
         Brain.Screen.setPenColor(vex::color::white);
        Brain.Screen.setFillColor(vex::color::green);
        Brain.Screen.drawRectangle(280, 20, 420, 100);
            //press button 1
            if (60 <= Brain.Screen.xPosition <= 200) && (20 <= Brain.Screen.yPosition <= 100) {
               
                if buttonpressed != 1 {
                    buttonpressed = 1;
                
                }
                
                if buttonpressed == 1 {
                     buttonpressed = 0;
                }
            }
            //press button 2
             if (280 <= Brain.Screen.xPosition <= 420) && (20 <= Brain.Screen.yPosition <= 100) {
                if buttonpressed != 2 {
                    buttonpressed = 2;
                
                }
                
                if buttonpressed == 2 {
                     buttonpressed = 0;
                }
                
             }
        
           //is this the reset thing needed?
            if buttonpressed == 1 {
                arm.setTimeout(0,  vex::timeUnits::sec);
                front_right.setTimeout(0,  vex::timeUnits::sec);
                rear_right.setTimeout(0,  vex::timeUnits::sec);
                rear_left.setTimeout(0,  vex::timeUnits::sec);
                front_left.setTimeout(0,  vex::timeUnits::sec);
            }
        //nothing for this yet
        if buttonpressed == 2 {
            
        }
        
        
        //To change movement controls
        
        if (controller.ButtonA.pressing) {
            
            if (drive_type < 2) {
                drive_type + 1;
            }
            
            else {
                drive_type = 0;
            }
        }
       
        
        
        if (controller.ButtonR1.pressing() == false) {
            
            
            
            
            //Control Type #1 - right joystick moves right wheel, left joystick moves left wheel
            
            if drive_type == 0 {
                rear_left.setVelocity(Controller.Axis3.position());
            rear_right.setVelocity(Controller.Axis2.position());
            rear_left.spin();
            rear_right.spin();
            front_right.setVelocity(Controller.Axis2.position());
            front_left.setVelocity(Controller.Axis3.position());
            front_right.spin();
            front_left.spin();
            
            }
            
            //Control Type #2 - right joystick left and right is turn left and right, left joystick up and down is forward and backwards
            
            if drive_type == 1 {
                
                if (controller.Axis1.position == 0) {
                    front_right.setVelocity(controller.Axis3.position);
                    rear_right.setVelocity(controller.Axis3.position);
                    front_left.setVelocity(controller.Axis3.position);
                    rear_left.setVelocity(controller.Axis3.position);
                }
                
                if (controller.Axis1.position != 0) {
                    
                    
                    
                front_right.setVelocity(controller.Axis1.position, velocityUnits);
                front_left.setVelocity(controller.Axis1.position, velocityUnits);
                rear_right.setVelocity(controller.Axis1.position, velocityUnits);
                rear_left.setVelocity(controller.Axis1.position, velocityUnits);
                
            }
                
                
                
            }
            
            //Control Type #3 - only right joystick, up and down is forward and back, left and right and diagonal all work
            
            if drive_type == 2 {
                
                 if (controller.Axis1.position > 0) {
            right_turn_var = controller.Axis1.position();
            speed_right = abs(controller.Axis2.position() - abs(right_turn_var));
            rear_right.setVelocity(speed_right);
            front_right.setVelocity(speed_right);
        }
        
        if (controller.Axis1.position < 0) {
            left_turn_var = controller.Axis1.position();
            speed_left = abs(controller.Axis2.position() - abs(left_turn_var));
            rear_left.setVelocity(speed_left);
            front_left.setVelocity(speed_left);
        }
        
        if (controller.Axis1.position == 0) {
            right_turn_var = 0;
            left_turn_var = 0;
            speed_right = 0;
            speed_left = 0;
            rear_left.setVelocity(controller.Axis2.position());
            front_left.setVelocity(controller.Axis2.position());
            rear_left.setVelocity(controller.Axis2.position());
            front_left.setVelocity(controller.Axis2.position());
        }
            
            rear_left.spin();
            rear_right.spin();
            front_left.spin();
            front_right.spin();    
                
                
                
            }
            
            }
            
           
            
            //not sure about other controls, someone tell me what needs to be done
            
            
            if (controller.ButtonL1.pressing) {
                arm.spin(fwd)
            }
            
            if (controller.ButtonL2.pressing) {
                arm.spin(rev)
            }
            
            
            
            
            
            
            
            
            
            
            
            
            
           
            
            
        }
        



    }
}

int main() {
    // Do not adjust the lines below

    // Set up (but don't start) callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(drivercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Robot Mesh Studio runtime continues to run until all threads and
    // competition callbacks are finished.
}
