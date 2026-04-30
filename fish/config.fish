if status is-interactive
    # Commands to run in interactive sessions can go here
end
set fish_greeting
alias v="nvim"
alias hx="helix"

export EDITOR="helix"
export SHELL="/bin/fish"

function fish_mode_prompt
end
export TERM="xterm-256color"
fish_vi_key_bindings
alias gittree="git log --all --topo-order --graph --show-signature"
fzf --fish | source
