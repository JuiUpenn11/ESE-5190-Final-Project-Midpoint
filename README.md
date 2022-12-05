# ESE-5190-Final-Project-Midpoint

The name of our project is Whack-It-First. It is adapted from the well-known Whack-A-Mole game. While we are in the process of improving the gaming experience for our audience, I would like to give a brief description of our progress so far.

Description of progress made till the day of demonstration:

Our main goal was to build a complete product while building this game. Keeping this in mind we started with the design of the outer case of our game which would hold the circuitry and also form the gaming interface. We first sketched the design of how we would like our game to look. As our game involves arcade buttons and a TFT screen, we looked up their schematics online in order to get a rough estimate of the measurements. We then sketched the design on paper. Once we had taken care of all the measurements along with a margin for error, we then designed the box using MakerCase. We then downloaded the .dxf file and imported it to Illustrator and then inserted the holes that would hold our arcade buttons and a rectangular space that would hold our TFT screen. We then got our design laser cut and chose to go ahead with MDF for the material for our demo day. Below is a picture of the top view of our gaming interface.

![Top view of box](https://user-images.githubusercontent.com/114092868/205559240-19f7006b-8dce-4f17-968e-a5b22cc3691e.jpeg)

We chose to work with the Raspberry Pi Pico H microcontroller board. We have chosen to build our code in Arduino IDE. So far, we have successfully built the code for a two player game with no latency. Since we are using the 1x4 LED Arcade Buttons STEMMA QT board to reduce the number of connections going from the arcade buttons to the Pico board, programming this was quite difficult. We tackled this task in slots. Since a single 1x4 LED Arcade Buttons STEMMA QT board is responsible for 4 arcade buttons, we first built the code to check if the buttons were illuminating on pressing. Once this was done we then built the code for a single player using 4 arcade buttons. Since this involved only a single board we could maintain the predefined address of the board as 0x3A. Once this was successfully implemented, we then integrated the code for the TFT display to display the instructions and scores for a single player. Later we proceeded to integrate the code for the speaker which would play twice, once at the beginning of the game and then at the end of the game. The integration of all the 3 tasks required a lot of troubleshooting as our goal was to completely eliminate delay. Once this was achieved for a single player, we moved onto integrating the second 1x4 LED Arcade Buttons STEMMA QT board which introduced 4  buttons for the second player. As all the 1x4 LED Arcade Buttons STEMMA QT boards have predefined pins to which the connections need to be made for the arcade buttons to work properly, we had to cut the PCB trace for the second board such that its address permanently got defined as 0x3B. We then had to strategically integrate the code for the second player in a way that the buttons would glow randomly for both and whenever hit correctly by either of them would record a score increment and this would continue till the wait time got over. The final score then would be displayed thus declaring the winner of the game.  We also built a power management circuit as our circuitry required 5V supply. We implemented all of this before our midpoint check demonstration. 

code/

working/

Following are the links of the codes we used at the beginning of the project. However, a lot of modifications had to be made due to the difference in the microcontroller board and number of players involved in the game.

https://www.instructables.com/Simon-Whack-a-Mole-Game-Using-Arduino/

https://electroniclab.tech.blog/2018/10/12/whac-a-button-with-arduino/

in-progress/

Following is the file to our code for the implementation of our two player game with the speaker and TFT display functionalities integrated.

[main-code.zip](https://github.com/JuiUpenn11/ESE-5190-Final-Project-Midpoint/files/10150941/main-code.zip)

libraries/

Following are the libraries we have used for our code. Kindly view the attached files.

1) Adafruit_GFX.h
2) Adafruit_seesaw.h
3) Adafruit_ST7735.h
4) seesaw_neopixel.h

reference/

https://www.instructables.com/Simon-Whack-a-Mole-Game-Using-Arduino/

https://electroniclab.tech.blog/2018/10/12/whac-a-button-with-arduino/


media/

materials/

Following is a list of components we have used till now in our project:

1)MDF material for the casing

2)Raspberry Pi Pico H

3)Medium sized illuminating arcade buttons 30mm (10) - Adafruit

4)Medium sized non-illuminated arcade button 30 mm (1) - Adafruit

5)1x4 LED Arcade Buttons STEMMA QT board (3)

6)1.8" Color TFT LCD display with MicroSD Card Breakout - ST7735R

7)AST-03208MR-R 32mm Speaker

8)Jumper Wires

Power Management Circuit components:

1)9V wall adapter

2)LM7805 voltage regulator

3)Breadboard Jack Barrel

4)0.33uF and 0.1uF capacitors

5)LED

6)330 ohm resistor

Following are the images of the main components used.

1) Raspberry Pi PICO H

![Pico](https://user-images.githubusercontent.com/114092868/205560135-7273437b-a814-4bfc-8b29-9e6a9131b56a.jpeg)

2) 1x4 LED Arcade Buttons STEMMA QT Board

![1x4 LED Arcade Buttons STEMMA QT](https://user-images.githubusercontent.com/114092868/205560272-cff7f640-4b45-4292-9e81-84b60cc219e1.jpeg)

3) Aracde Button

![Aracde button connection](https://user-images.githubusercontent.com/114092868/205560328-79428c63-81d9-4140-a9fd-0be68a6f0fc9.jpeg)

4) TFT Display

![TFT display](https://user-images.githubusercontent.com/114092868/205560382-391ff19e-7802-47f9-be41-18d69ce757fa.jpeg)

5) Speaker

![Speaker](https://user-images.githubusercontent.com/114092868/205560419-46d00af3-9503-40fc-8f9c-36935b6732b9.jpeg)

design/

Following are the files we built to get our gaming box laser cut. First file which is .dxf was built in MakerCase, second file which is .ai was built in illustrator.

[box.zip](https://github.com/JuiUpenn11/ESE-5190-Final-Project-Midpoint/files/10150943/box.zip)

[box to laser cut.zip](https://github.com/JuiUpenn11/ESE-5190-Final-Project-Midpoint/files/10150944/box.to.laser.cut.zip)

troubleshooting/

Since we chose to work in the Arduino IDE we did troubleshooting using its serial monitor. Following image is an example of that.

![Serial Monitor Troubleshooting](https://user-images.githubusercontent.com/114092868/205558203-c697efdf-3896-4e9b-8b8a-61e6d9f17a9d.jpeg)

demos/

Following are the videos showing the successful demonstration of our implementation so far.

https://user-images.githubusercontent.com/114092868/205558321-53f5b81d-b825-498e-a80f-88a762aa86df.mp4

https://user-images.githubusercontent.com/114092868/205558398-f9ce3012-6d98-4aab-8a88-b12d2db3f1b6.mp4

https://user-images.githubusercontent.com/114092868/205558437-e8d6be01-8277-4dab-88f3-297affa62e00.mp4

diagrams/

All our connections in the circuitry were built with reference to the following pin diagrams. Following are the images for the same. Following is the schematic of the power management circuit built for 5V supply.

![PICO pin diagram](https://user-images.githubusercontent.com/114092868/205558705-b6ddb13c-8510-4575-a89f-99ab86bbe387.jpeg)

![Arcade Button connections pin diagram](https://user-images.githubusercontent.com/114092868/205558750-ce3c9473-e681-437c-b3d6-631aa6ed3510.jpeg)

![Power management circuit](https://user-images.githubusercontent.com/114092868/205558803-88df5b2a-4ba3-4ed7-98ea-b735f204677f.png)













