import type { SourceInstance } from './source_instance';

/**
 * Calls the NDI API to retrieve a list of {@link SourceInstance}s
 * exposed into the network.
 * @param timeout The maximum timeout to keep waiting for the list of sources
 */
export function findSources (timeout?: number): Promise<SourceInstance[]>;
