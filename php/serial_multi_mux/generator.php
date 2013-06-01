<?php

require_once('php_serial.class.php');

declare(ticks = 1);

define(
    'SLEEP_SECONDS',
    (count($argv) == 2 ? (float) $argv[1] : 0.25)
);

// Capture Ctrl-C
pcntl_signal(SIGINT, 'signal_handler');


$units = array(
    array(
        'actual' => 0,
        'range' => array('low' => 50, 'high' => 58)
    ),
    array(
        'actual' => 0,
        'range' => array('low' => 60, 'high' => 68)
    ),
);


function getSerialConnection()
{
    static $serial = null;

    if (! $serial) {
        print "Opening serial connection .. ";
        $serial = new phpSerial();
        if ($serial->deviceSet('/dev/ttyACM0')) {
                $serial->confBaudRate(9600);
                $serial->deviceOpen();
        } else {
            print "ERROR\n";
            exit(1);
        }
        print "OK\n";
    }
    return $serial;
}

function signal_handler($signo)
{
    print "Closing serial connection .. ";
    $serial = getSerialConnection();
    print ($serial->deviceClose() ? "OK\n" : "ERROR\n");
    exit(0);
}

function get_next_value($actual, $range)
{
    if ($actual < $range['low']) {
        $next = rand($range['low'], $range['high']);
    } else {
        $next = $actual + rand(-1, 1);
    }

    if ($next < $range['low']) {
        $next = $range['low'] + 1;
    }
    if ($next > $range['high']) {
        $next = $range['high'] - 1;
    }

    return $next;
}

function loop($units)
{
    printf("Loop every %ss\n", SLEEP_SECONDS);
    $serial = getSerialConnection();

    while (true) {
        foreach ($units as &$unit) {
            $unit['actual'] = get_next_value(
                $unit['actual'], $unit['range']
            );
            print "Sending {$unit['actual']} .. ";
            $value = chr($unit['actual']);
            $serial->sendMessage($value);
            print "OK\n";
            usleep(SLEEP_SECONDS * 1000000);
        }
    }
}

loop($units);
