<?php
//Declaration des fonctions
  function test1($i, $j){
     echo ("i = " . $i);
     echo ("j = " . $j);
  }

  function test2($j){
     echo ("j = " . $j);

     j = $_GET[j];
     echo ("j = " . $j);
  }

//Début Procedure principale
  test1(5, 6);
  $j = 4;
  test2($j);
  test1(5, $j);
//Fin Procedure principale
  ?>
