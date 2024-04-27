int readHeadSick(){   //( truc y )
  return headSickKal.updateEstimate(analogRead(A7))*one_dist + 200;
}
int readRightSick(){   // san phai gan den xa: 355 , 1150, 1910, 2670, 3410   ( truc x )
  return rightSickKal.updateEstimate(analogRead(A6))*one_dist + 200;
}
int readLeftSick(){   // san phai gan den xa: 355 , 1150, 1910, 2670, 3410   ( truc x )
  return leftSickKal.updateEstimate(analogRead(A8))*one_dist + 200;
}


