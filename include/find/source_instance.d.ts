import { TallyState } from '../structures/tally_state';

export interface SourceInstance {
    setTally (tallyState: TallyState): void;

    get ipAddress(): string;
    get name(): string;
    get urlAddress(): string;
}
