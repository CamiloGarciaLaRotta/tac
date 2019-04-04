const path = require("path");
const CopyWebpackPlugin = require("copy-webpack-plugin");

const outputDir = path.join(__dirname, "build/");

module.exports = {
  entry: {
    popup: "./lib/js/src/popup.bs.js",
    contentScript: "./lib/js/src/ContentScript.bs.js"
  },
  mode: "production",
  output: {
    path: outputDir,
    filename: "[name].js"
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
