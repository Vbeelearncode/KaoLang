import createKaoLang from './kaolang.js';

document.addEventListener('DOMContentLoaded', async () => {
    const programBox = document.getElementById('programBox');
    const inputBox = document.getElementById('inputBox');
    const outputBox = document.getElementById('outputBox');
    const runButton = document.getElementById('runButton');

    const slButton = document.getElementById('kao-sl');
    const srButton = document.getElementById('kao-sr');
    const nandButton = document.getElementById('kao-nand');
    const lstartButton = document.getElementById('kao-lstart');
    const lendButton = document.getElementById('kao-lend');
    const writeButton = document.getElementById('kao-write');
    const readButton = document.getElementById('kao-read');
    const mrButton = document.getElementById('kao-mr');
    const mlButton = document.getElementById('kao-ml');
    const regButton = document.getElementById('kao-reg');


    slButton.onclick = () => { programBox.value += '👈(ﾟヮﾟ👈)'; };
    srButton.onclick = () => { programBox.value += '(👉ﾟヮﾟ)👉'; };
    nandButton.onclick = () => { programBox.value += '👈(⌒▽⌒)👉'; };
    lstartButton.onclick = () => { programBox.value += '(ヘ･_･)ヘ┳━┳'; };
    lendButton.onclick = () => { programBox.value += '(╯°□°）╯︵ ┻━┻'; };
    writeButton.onclick = () => { programBox.value += '✍️(◔◡◔)'; };
    readButton.onclick = () => { programBox.value += '(⓿_⓿)'; };
    mrButton.onclick = () => { programBox.value += 'o(( >ω<))o'; };
    mlButton.onclick = () => { programBox.value += 'o((>ω< ))o'; };
    regButton.onclick = () => { programBox.value += 'ᕦ(ò_óˇ)ᕤ'; };

    const Module = await createKaoLang({
        print: (text) => { outputBox.textContent += text + '\n'; },
        printErr: (text) => { outputBox.textContent += 'Error: ' + text + '\n'; },
    });
    console.log('After await:');
    console.log('Module keys:', Object.keys(Module));
    console.log('callMain typeof:', typeof Module.callMain);
    console.log('has FS:', !!Module.FS);
    console.log('onRuntimeInitialized:', typeof Module.onRuntimeInitialized);

    runButton.onclick = async () => {
        const program = programBox.value;
        const input = inputBox.value;

        try {
            // Write files to the in-memory filesystem
            Module.FS.writeFile('program.kao', new TextEncoder().encode(program));
            Module.FS.writeFile('input.txt', new TextEncoder().encode(input));
            Module.FS.writeFile('output.txt', new TextEncoder().encode(''));

            // Check that they really exist
            console.log('FS files:', Module.FS.readdir('.'));

            // Run KaoLang
            Module.callMain(['program.kao', 'input.txt', 'output.txt']);
            
            // Read the output file
            const outputData = Module.FS.readFile('output.txt', { encoding: 'utf8' });
            outputBox.textContent += outputData;
        } catch (err) {
            console.error('Run failed:', err);
            outputBox.textContent += 'Runtime Error: ' + err + '\n';
        }
    };

});