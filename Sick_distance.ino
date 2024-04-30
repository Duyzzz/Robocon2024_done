int readHeadSick(){   //( truc y )
  return headSickKal.updateEstimate(analogRead(A11))*one_dist + 100;
}
int readRightSick(){   // san phai gan den xa: 355 , 1150, 1910, 2670, 3410   ( truc x )
  return rightSickKal.updateEstimate(analogRead(A9))*one_dist/2 + 100;
}
int readLeftSick(){   // san phai gan den xa: 355 , 1150, 1910, 2670, 3410   ( truc x )
  return leftSickKal.updateEstimate(analogRead(A10))*one_dist/2 + 100;
}


