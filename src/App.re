type state = {loading: bool};

type action =
  | DidMount;

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  reducer: (action, _state) =>
    switch (action) {
    | DidMount => ReasonReact.Update({loading: false})
    },
  initialState: () => {loading: false},
  render: self =>
    <div className="app">
      {self.state.loading
         ? <div className="login-size"> <div className="loader" /> </div>
         : <JobApp />}
    </div>,
};
