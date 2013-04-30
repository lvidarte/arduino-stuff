<?php
if (isset($_GET['action'])) {
    require_once('php_serial.class.php');

    $action = $_GET['action'];
    $msec = isset($_GET['msec']) ? $_GET['msec'] : 500000;
    $times = isset($_GET['times']) ? $_GET['times'] : 5;

    $serial = new phpSerial();
    $serial->deviceSet('/dev/ttyUSB1');
    $serial->confBaudRate(9600);
    $serial->deviceOpen();

    $actions = array('on' => "1\r", 'off' => "0\r");

    if (in_array($action, array_keys($actions))) {
        $serial->sendMessage($actions[$action]);
    }
    if ($action == 'blink') {
        for ($i = 1; $i <= $times * 2; $i++) {
            $_action = ($i % 2 ? 'on' : 'off');
            $serial->sendMessage($actions[$_action]);
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
    <title>Arduino LED control</title>
</head>
<body>
    <h1>Arduino LED control</h1>
    <ul>
        <li><a href="arduino.php?action=on">On</a></li>
        <li><a href="arduino.php?action=off">Off</a></li>
    </ul>
    <h2>Blink</h2>
    <ul>
        <li><a href="arduino.php?action=blink">Slow</a></li>
        <li><a href="arduino.php?action=blink&msec=100000&times=10">Fast</a></li>
    </ul>
</body>
</html>
