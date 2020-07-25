
export interface IMessageToHost {
    type: "messageToHost";
    data: string;
}

export type HostPluginEventTypes = IMessageToHost;