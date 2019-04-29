<?php
session_start();

echo  $_GET['Name']; 
echo  $_POST['Name']; 
echo  $_REQUEST['Name']; 
$timestamp = date("d-m-Y - H:i:s");
$datastring = $_POST["params"];
$myfile = fopen("newfile.txt", "w") or die("Unable to open file!");
$txt = $timestamp . " - ".$datastring."\n";
fwrite($myfile, $txt);
fclose($myfile);
echo $txt;
?>	
