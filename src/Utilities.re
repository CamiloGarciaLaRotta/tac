/** Convert value from event to string
One of the disadvantages from reason is that you have to do this type casting */
let valueFromEvent = evt => ReactEvent.Form.target(evt)##value;

let str = ReasonReact.string;

[@bs.deriving abstract]
type tabURL = {url: string};

[@bs.val] external createTab: tabURL => unit = "chrome.tabs.create";
