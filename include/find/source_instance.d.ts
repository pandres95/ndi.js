import { TallyState } from '../structures/tally_state';

/**
 * An instance of an NDI (sender/receiver) source
 */
export interface SourceInstance {
    /** Sets the tally state of the source instance */
    setTally (tallyState: TallyState): void;

    /** Retrieves the IP Address of the instance */
    get ipAddress(): string;
    /** Retrieves the name of the instance */
    get name(): string;
    /** Retrieves the URL Address of the instance */
    get urlAddress(): string;
}
