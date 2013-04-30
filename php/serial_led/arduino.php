<?php
if (isset($_GET['action'])) {
    require_once('php_serial.class.php');

    $action = $_GET['action'];
    $msec = isset($_GET['msec']) ? $_GET['msec'] : 250000;
    $times = isset($_GET['times']) ? $_GET['times'] * 2 : 10;

    $serial = new phpSerial();
    $serial->deviceSet('/dev/ttyUSB0');
    $serial->confBaudRate(9600);
    $serial->deviceOpen();

    $actions = array('on' => "1\r", 'off' => "0\r");

    if (in_array($action, array_keys($actions))) {
        $serial->sendMessage($actions[$action]);
    }
    if ($action == 'blink') {
        for ($i = 1; $i <= $times; $i++) {
            $j = ($i % 2 ? 'on' : 'off');
            $serial->sendMessage($actions[$j]);
            usleep($msec);
        }
    }
    $serial->deviceClose();
}
?>
<!doctype html>
<html>
<head>
    <meta charset="utf-8">
    <title>Serial</title>
</head>
<body>
    <ul>
        <li><a href="arduino.php?action=on" title="">On</a></li>
        <li><a href="arduino.php?action=off" title="">Off</a></li>
        <li><a href="arduino.php?action=blink&msec=250000&times=5" title="">Blink</a></li>
    </ul>
</body>
</html>
