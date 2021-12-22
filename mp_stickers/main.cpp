#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

int main() {

  std::cout << "reading base" << std::endl;
  Image base;
  base.readFromFile("Tropical_Background.png");

  std::cout << "reading sticker1" << std::endl;
  Image sticker1;
  sticker1.readFromFile("Matcha_green_tea.png");

  std::cout << "reading sticker2" << std::endl;
  Image sticker2;
  sticker2.readFromFile("Fried_Chicken.png");

  std::cout << "reading sticker3" << std::endl;
  Image sticker3;
  sticker3.readFromFile("thumbs_up.png");


  StickerSheet output(base, 3);

  output.addSticker(sticker1, 0,0);
  output.addSticker(sticker2, 50,50);
  output.addSticker(sticker3, 100,100);

  Image final_Output = output.render();
  final_Output.writeToFile("myImage.png");


  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
