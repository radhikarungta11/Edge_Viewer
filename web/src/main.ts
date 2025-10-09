const fpsEl = document.getElementById('fps')!;
const resEl = document.getElementById('res')!;
const imgEl = document.getElementById('frame') as HTMLImageElement;

const sampleBase64 = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAAB...'; // replace with your Android-exported frame
imgEl.src = sampleBase64;
resEl.textContent = '1280x720';

let frames = 0, last = performance.now();
function tick(){
  frames++; const now = performance.now();
  if (now - last >= 1000){ fpsEl.textContent = String(frames); frames = 0; last = now; }
  requestAnimationFrame(tick);
}
requestAnimationFrame(tick);
