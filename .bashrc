#
# ~/.bashrc
#

ip link set eth0 up
dhcpcd
sh code/autostart.sh

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
