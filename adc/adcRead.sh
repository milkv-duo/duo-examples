#!/bin/sh

saradc_path=$(find / -name "cv180x_saradc.ko" 2>/dev/null)

insmod $saradc_path
