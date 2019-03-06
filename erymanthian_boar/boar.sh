#!/bin/bash
#atrun_plist=/System/Library/LaunchDaemons/com.apple.atrun.plist
#sudo sed -i '' 's/true/false/g' $atrun_plist
#sudo launchctl unload -F $atrun_plist
#sudo launchctl load -F $atrun_plist
#
#   These commands enable the at command to run on OSX. Can'd do shit without sudo, 
#   but they are enabled on our machines.
#
echo "42" | at 08:42 AM 12/21/2019
# use at -l to list