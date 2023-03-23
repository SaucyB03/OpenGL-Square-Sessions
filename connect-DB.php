
<!-- connect-db.php -->
<?php
$databaseName = 'KJABLON4_cs120_mod3OE';
$dsn = 'mysql:host=webdb.uvm.edu;dbname=' . $databaseName;
$username = 'kjablon4_writer';
$password = '7TqqJNmLz1M5';
$pdo = new PDO($dsn, $username, $password);
?>
<!-- Connection complete -->
