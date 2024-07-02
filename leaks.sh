#!/bin/bash

./minishell &
MINISHELL_PID=$!

while kill -0 $MINISHELL_PID 2> /dev/null; do
    leaks minishell
    sleep 1
done

leaks minishell

echo "minishell has exited. Memory leak detection stopped."