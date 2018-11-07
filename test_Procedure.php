<?php
//Declaration des fonctions
  function test1($i, $h){
     echo ("i = " . $i);
     echo ("h = " . $h);
  }

  function test2($j){
     echo ("j = " . $j);

     j = $_GET[j];
     echo ("j = " . $j);
  }

//Début Procedure principale
  test1(5, 6);
  $j = 4;
  $oooo = 888;
  test2($j);
  test1($oooo, $j);
//Fin Procedure principale
  ?>
