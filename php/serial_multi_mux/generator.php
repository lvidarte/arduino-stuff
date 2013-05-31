<?php

require_once('php_serial.class.php');

$serial = new phpSerial();
if ($serial->deviceSet('/dev/ttyACM0')) {
        $serial->confBaudRate(9600);
        $serial->deviceOpen();
} else {
    print "Error opening serial device.\n";
    exit(1);
}

declare(ticks = 1);

define('MSEC', (count($argv) == 2 ? (int) $argv[1] : 250000));
printf("Every %d microseconds\n", MSEC);


$units = array(
    array(
        'actual' => 0,
        'range' => array(
            'low' => 50,
            'high' => 58
        )
    ),
    array(
        'actual' => 0,
        'range' => array(
            'low' => 60,
            'high' => 68
        )
    ),
);


function signal_handler($signo)
{
    print "Saliendo ..\n";
    //$serial->deviceClose();
    exit(0);
}


// Capture Ctrl-C
pcntl_signal(SIGINT, 'signal_handler');


function get_next_value($actual, $range)
{
    if ($actual < $range['low']) {
        $next = rand($range['low'], $range['high']);
    } else {
        $next = $actual + rand(-1, 1);
    }

    if ($next < $range['low']) {
        $next = $range['low'];
    }
    if ($next > $range['high']) {
        $next = $range['high'];
    }

    #printf("(%d, %d)\n", $actual, $next);
    return $next;
}


while (true) {
    foreach ($units as &$unit) {
        $unit['actual'] = get_next_value(
            $unit['actual'], $unit['range']
        );
        printf("Sending %d ..\n", $unit['actual']);
        $serial->sendMessage(chr($unit['actual']));
        usleep(MSEC);
    }
}

