<?php
$value = isset($_GET['value']) ? $_GET['value'] : 0;

if (isset($_GET['value'])) {
    require_once('php_serial.class.php');

    $serial = new phpSerial();
    $serial->deviceSet('/dev/ttyUSB0');
    $serial->confBaudRate(9600);
    $serial->deviceOpen();

    $serial->sendMessage($_GET['value']);
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
    <select name="brigthness" onchange="javascript:location.href='arduino.php?value='+this.value">
        <?php for ($i = 0; $i <= 9; $i++) { ?>
        <option value="<?= $i ?>" <?= ($i == $value) ? 'selected="selected"' : '' ?>><?= $i ?></option>
        <? } ?>
    </select>
</body>
</html>
