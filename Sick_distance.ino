int readHeadSick(){   //( truc y )
  return (float)headSickKal.updateEstimate(analogRead(A9))*4.88 + (float)100;
}
int readRightSick(){   // san phai gan den xa: 355 , 1150, 1910, 2670, 3410   ( truc x )
  return (float)rightSickKal.updateEstimate(analogRead(A10))*4.88 + (float)100;
}
int readLeftSick(){   // san phai gan den xa: 355 , 1150, 1910, 2670, 3410   ( truc x )
  return (float)leftSickKal.updateEstimate(analogRead(A11))*4.88 + (float)100;
}


