#!/bin/bash

echo "🚀 Testing Multiple Redirections"
echo "================================"

# Test 1: Heredoc básico
echo "Test 1: Basic heredoc"
echo "cat << EOF
Contenido del heredoc
segunda línea
EOF
exit" | ./minishell

echo ""
echo "Test 2: Heredoc + pipe"
echo "cat << EOF | wc -l
línea 1
línea 2
línea 3
EOF
exit" | ./minishell

echo ""
echo "Test 3: Heredoc + redirección de salida"
echo "cat << EOF > output.txt
Este texto va al archivo
segunda línea del archivo
EOF
cat output.txt
rm -f output.txt
exit" | ./minishell

echo ""
echo "Test 4: Heredoc + pipe + redirección"
echo "cat << EOF | grep línea > resultado.txt
primera línea
segunda línea
tercera línea diferente
EOF
cat resultado.txt
rm -f resultado.txt
exit" | ./minishell

echo ""
echo "Test 5: Múltiples heredocs"
echo "cat << EOF1 > archivo1.txt
Contenido del primer heredoc
EOF1
cat << EOF2 > archivo2.txt
Contenido del segundo heredoc
EOF2
cat archivo1.txt archivo2.txt
rm -f archivo1.txt archivo2.txt
exit" | ./minishell

echo ""
echo "Test 6: Heredoc + append"
echo "echo 'Primera línea' > test.txt
cat << EOF >> test.txt
Segunda línea desde heredoc
Tercera línea desde heredoc
EOF
cat test.txt
rm -f test.txt
exit" | ./minishell

echo ""
echo "Test 7: Combinación compleja"
echo "cat << EOF | sort | uniq | wc -l
zebra
apple
banana
apple
zebra
cherry
EOF
exit" | ./minishell

echo ""
echo "✅ All redirect tests completed!"
