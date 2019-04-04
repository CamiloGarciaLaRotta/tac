const path = require("path");
const CopyWebpackPlugin = require("copy-webpack-plugin");

const outputDir = path.join(__dirname, "build/");

module.exports = {
  entry: "./lib/js/src/popup.bs.js",
  mode: "production",
  output: {
    path: outputDir,
    filename: "index.js"
  },
  plugins: [
    new CopyWebpackPlugin([
      { from: "manifest.json" },
      { from: "icon.png" },
      { from: "popup.html" },
      { from: "./src/App.css" }
    ])
  ]
};
