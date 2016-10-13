<?php

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

$value = isset($_GET['value']) ? $_GET['value'] : 0;

if (isset($_GET['action'])) {
    require_once('php_serial.class.php');

    $action = $_GET['action'];
    $msec = isset($_GET['msec']) ? $_GET['msec'] : 500000;

    $serial = new phpSerial();
    $serial->deviceSet('/dev/ttyUSB0');
    $serial->confBaudRate(9600);
    $serial->deviceOpen();

    if ($action == 'set') {
        $serial->sendMessage($value);
    }
    if ($action == 'dimmer') {
        for ($i = 0; $i <= 9; $i++) {
            $serial->sendMessage($i);
            usleep($msec);
        }
        for ($i = 9; $i >= 0; $i--) {
            $serial->sendMessage($i);
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
    Set brightness
    <select
        onchange="javascript:location.href='arduino.php?action=set&value='+this.value">
        <?php for ($i = 0; $i <= 9; $i++) { ?>
            <option value="<?= $i ?>"
            <? if ($i == $value) echo 'selected="selected"'; ?>>
                <?= $i ?>
            </option>
        <? } ?>
    </select>
    <h2>Dimmer</h2>
    <ul>
        <li><a href="arduino.php?action=dimmer&msec=500000">Slow</a></li>
        <li><a href="arduino.php?action=dimmer&msec=100000">Fast</a></li>
    </ul>
</body>
</html>
