#!/bin/sh
saradc_path_cv180x=$(find / -name "cv180x_saradc.ko" 2>/dev/null)
saradc_path_cv181x=$(find / -name "cv181x_saradc.ko" 2>/dev/null)

if (lsmod | grep -q "cv180x_saradc") || (lsmod | grep -q "cv181x_saradc") ;then
        echo "SARADC module already loaded."
        echo "Define the ADC channel:
                1: ADC1 (GP26|PIN31)
                2: ADC2 (GP27|PIN32)
                3: ???
                4: VDDC_RTC
                5: PWR_GPIO1
                6: PWR_VBAT_"
        read adc_channel

        if [[ $adc_channel =~ ^[1-6]+$ ]]; then
                echo "Enabling Channel $adc_channel"
                echo $adc_channel > /sys/class/cvi-saradc/cvi-saradc0/device/cv_saradc
                while true; do
			echo "ADC $adc_channel read: $(cat /sys/class/cvi-saradc/cvi-saradc0/device/cv_saradc)"
        		sleep 1
		done
	else
                echo "Invalid ADC Channel."
        fi

else
        insmod $saradc_path_cv180x >/dev/null
        insmod $saradc_path_cv181x >/dev/null
        echo "SARADC module loaded."
        echo "Define the ADC channel:
                1: ADC1 (GP26|PIN31)
                2: ADC2 (GP27|PIN32)
                3: ???
                4: VDDC_RTC
                5: PWR_GPIO1
                6: PWR_VBAT_"
        read adc_channel

        if [[ $adc_channel =~ ^[1-6]+$ ]]; then
                echo "Enabling Channel $adc_channel"
                echo $adc_channel > /sys/class/cvi-saradc/cvi-saradc0/device/cv_saradc
               	while true; do
			echo "ADC $adc_channel read: $(cat /sys/class/cvi-saradc/cvi-saradc0/device/cv_saradc)"
        		sleep 1
		done
	else
                echo "Invalid ADC Channel."
        fi
fi
