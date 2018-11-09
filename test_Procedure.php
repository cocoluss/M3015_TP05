<?php
//Declaration des fonctions et procédures
  function test1($i, $h){
     echo ("appel procedure test1");
     echo ("i = " . $i);
     echo ("h = " . $h);
  }

  function test2($j){
     echo ("appel procedure test2 (return j)");
     $j++;
     echo ("j = " . $j);
  }

//Début Procedure principale
  test1(5, 6);
  $j = 4;
  $oooo = 888;
  test1($oooo, $j);
  echo ("o = appel test2(1);");
  $o = test2(1);;
  test2(5);
  echo ("o = " . $o);
  echo ("o = appel test2(1);");
  $o = test2(7);;
  echo ("o = " . $o);
//Fin Procedure principale
  ?>
