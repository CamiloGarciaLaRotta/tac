open Chrome.Extensions.Storage;

let clear = () => Sync.clear(() => ());

/** Store the id if it exists, clear the storage if not
 *  This ensures no expired ids are kept in storage */
let refreshId = maybeId =>
  switch (maybeId) {
  | Some(id) =>
    let uid = Js.Dict.empty();
    Js.Dict.set(uid, "id", Js.Json.string(id));
    Sync.set(uid, () => ());
  | None => clear()
  };

/** Store the token if it exists, clear the storage if not
 *  This ensures no expired tokens are kept in storage */
let refreshToken = maybeToken =>
  switch (maybeToken) {
  | Some(jwt) =>
    let token = Js.Dict.empty();
    Js.Dict.set(token, "token", Js.Json.string(jwt));
    Sync.set(token, () => ());
  | None => clear()
  };

/** return a promise to retrieve the saved token */
let getSavedId = () => {
  /** only unwrap a single string attribute */
  let unwrapStoreValue = maybeValue =>
    switch (maybeValue) {
    | Some(Js.Json.JSONString(v)) => Some(v)
    | None => None
    | _ => failwith("Expected id to be a string")
    };
  Js.Promise.make((~resolve, ~reject as _) =>
    Sync.get("id", items => {
      let restoredId =
        /** See https://developer.chrome.com/apps/storage#type-StorageArea
         *  We check chrome.runtime.lastError to ensure correctness even when API call fails */
        Js.Nullable.isNullable(Chrome.Runtime.lastError)
          ? Js.Dict.get(items, "id") |> unwrapStoreValue : None;
      resolve(. restoredId);
    })
    |> ignore
  );
};

/** return a promise to retrieve the saved token */
let getSavedToken = () => {
  /** only unwrap a single string attribute */
  let unwrapStoreValue = maybeValue =>
    switch (maybeValue) {
    | Some(Js.Json.JSONString(v)) => Some(v)
    | None => None
    | _ => failwith("Expected token to be a string")
    };
  Js.Promise.make((~resolve, ~reject as _) =>
    Sync.get("token", items => {
      let restoredToken =
        /** See https://developer.chrome.com/apps/storage#type-StorageArea
         *  We check chrome.runtime.lastError to ensure correctness even when API call fails */
        Js.Nullable.isNullable(Chrome.Runtime.lastError)
          ? Js.Dict.get(items, "token") |> unwrapStoreValue : None;
      resolve(. restoredToken);
    })
    |> ignore
  );
};
