const img = document.getElementById('img') as HTMLImageElement;
const stats = document.getElementById('stats') as HTMLDivElement;

// 2x2 base64 PNG placeholder
const base64Png = "iVBORw0KGgoAAAANSUhEUgAAAAIAAAACCAYAAABytg0kAAAADUlEQVQImWNgoC/wHwAE4gJ3YwFJmQAAAABJRU5ErkJggg==";

img.src = "data:image/png;base64," + base64Png;
stats.textContent = `Resolution: 2x2 • FPS: static sample`;
