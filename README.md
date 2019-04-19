# Camagotchi

## Overview
A remake of the famous Tamagotchi toy,the digital pet simulator, written in C. The program utilizes the ncurses and multithreading libraries to recreate this experience.

## Future Plans
I hope to add more features and more growth stages to the Camagotchi, and plan to 3D print a case and run the program on a Rapberry Pi Zero. I want to buttons to it so it mimics an actual Tamagotchi toy. I also want to optimize the program and change the length of all of the growth cycles so that it is more like that of a Tamagotchi

## Instructions
Navigate to the folder  
1. `make`  
1. `./camagotchi`

## Manual
The 'b' key is used to move the cursor, the 'n' key is used to select options, and the 'm' key is the back button

### FOOD
There are two options on the FOOD menu. The entree gives the Camagotchi a full heart of hunger while the snack gives a half heart of hunger. Be careful not to overfeed your pet, because it will then become sick. The Camagotchi has a chance to poop on the screen after eating

### LITE
This option turns the lights off, making the main screen black. None of the other menu options can be selected while the light is off

### PLAY
This option starts a game with the Camagotchi. The Camagotchi displays a number on the left side of the screen, and you have to try to guess whether or not the next number that appears is going to be higher or lower than the last one. Click 'b' to guess less than and 'n' to guess greater than. The numbers range from 0-9, and in the case that the new number that appears is the same as the last number, then it counts as a right answer, even if you guess higher or lower. Every right answer will raise the Camagotchi's happiness by half of a heart

### MEDS
This option is how you cure a sick Camagotchi. You know your pet is sick when it stops moving and its eyes are an '=' or a '-'. Sometimes it will take the Camagotchi multiple doses of medicine before it is cured. Be careful not to let your Camagotchi be sick for too long, because it dies after being sick for a certain length of time. If you try to use medicine on a Camagotchi who is not sick, then no animation occurs and its happiness goes down by half of a heart

### DUCK
This option is used to clean poop off of the screen. If poop is left on the screen for too long, then the Camagotchi will become sick

### HLTH
This option is used to check the Camagotchi's happiness and hunger levels. Click the select button to switch between the two displays. Both the Camagotchi's happiness and hunger bars have a maximum of for hearts, and can increase/decrease in increments of half of a heart. If a Camagotchi is at zero hunger for too long, then the Camagotchi may die

### DISC
This function is what you click when your Camagotchi calls for attention, but it is not actually at zero hunger or zero health. If you discipline a Camagotchi who when it doesn't deserve it, then its happiness goes down by down hearts

### ATTN
This option is not always available on the screen. The option lights up if the Camagotchi's hunger or happiness is at zero. It can also turn on if the Camagotchi wants attention, even if it is fully healthy. After you tend to the Camagotchi's needs, you can click the 'n' button to turn the attention button back off, until it calls for attention again. If it falsely calls for attention, you are supposed discipline the Camagotchi with the DISC menu option
