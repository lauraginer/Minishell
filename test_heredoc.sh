#!/bin/bash

echo "🚀 Testing Heredoc Hybrid Implementation"
echo "========================================"

# Test 1: Basic heredoc
echo "Test 1: Basic heredoc"
echo "cat << EOF
primera línea
segunda línea
EOF
exit" | ./minishell

echo ""
echo "Test 2: Heredoc with pipe"
echo "cat << EOF | wc -l
primera línea
segunda línea
tercera línea
EOF
exit" | ./minishell

echo ""
echo "✅ Tests completed!"
