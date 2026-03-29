const express = require('express');
const { spawn } = require('child_process');
const app = express();

app.get('/deleteBook', (req, res) => {
    const bookId = req.query.bookId;
    const cppProcess = spawn('.\\main.exe', [bookId]);

    let output = '';
    cppProcess.stdout.on('data', (data) => {
        output += data;
    });

    cppProcess.on('close', () => {
        res.send(output);  // send C++ cout output back to browser
    });
});

app.listen(3000, () => console.log('Server running on port 3000'));