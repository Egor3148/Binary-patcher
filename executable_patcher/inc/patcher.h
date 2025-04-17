//
//This module provides a method to patch a specific binary file 
// by writing to constant buffer in stack
// 
// The format of the buffer might be: <st    ...    st>
// The function simply looks for such segment in binary
// and writes to it.
// 
// 
//

#include <string>


// @brief Patches a binary file
// 
// @details 
// Steps:
// 1) Copies [source] file content until identifies buffer start token [<st]
// 2) Continues reading [source] file content, but writes [content] values
// 3) Step 2 continues until the end token [st>] or there's no content left
// 4) If patching finishes not because of reaching buffer limit, end token is written then
// 5) Copies the rest of the file (it's assumed that there's only one patchable buffer)
// 
// @paran content		[in] : content to write to buffer
// @param size			[in] : content size in bytes
// @param file_to_patch [in] : filepath to the file we want to patch
// @param file_patched	[in] : filepath to patched file (including name)
// 
// @returns integer code:
//	[0] : OK
//  [1] : Input file wasn't open
//  [2] : Output file wasn't open
//  [3] : Buffer to patch wasn't found
//  [4] : Patching finished because of buffer limit exceeded: possible loss of data
//
int patch(const char* content, int size, 
	std::string file_to_patch, std::string file_patched);

void signFile(const std::string& filename);