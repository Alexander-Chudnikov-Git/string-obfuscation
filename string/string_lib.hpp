#ifndef OBFUSCATED_STRING_HPP
#define OBFUSCATED_STRING_HPP

#include <memory>
#include <cmath>

class ObfuscatedString
{
public:
	ObfuscatedString();
	~ObfuscatedString();

	template<typename T, std::size_t N>
    		static constexpr const std::unique_ptr<T[]> cgi_r();
	template <typename T, std::size_t SIZE>
		static constexpr std::array<T, SIZE> uniform_distribution(T min, T max);
	template <typename T, std::size_t SIZE, std::size_t IRWIN_NUM = 12>
		static constexpr std::array<T, SIZE> normal_distribution();

	/**
	 * @brief       Encrypts string at comple time
	 *
	 * @param       initial_string  The initial string
	 * @param       string_length   Length on the initial string 
	 * @param       key             The key for encryption
	 * @param       key_length      Length on the encryption key
	 *
	 * @return      Encrypted string
	 */
	static constexpr const char* string_encrypt(const char* initial_string, std::size_t string_length, const char* key, std::size_t key_length)
	{
		std::size_t new_buffer_length = string_length + 2 + (string_length % 2);
		int offset = 0;

		char* encryptred_data = new char[new_buffer_length];
		char* encryption_buffer = new char[new_buffer_length]; 

		for(std::size_t index = 0; index < new_buffer_length; ++index)
	    {
	    	if (index == (new_buffer_length - 1) / 2)
	    	{
	    		encryption_buffer[index + offset] = key[new_buffer_length % key_length] ^ key[0];
	    		offset += 1;
	    	}
	    	else 
	    	{
	        	encryption_buffer[index] = initial_string[index - offset];
	        }
	    }

	    for(std::size_t index = 0; index < new_buffer_length; index += 2)
	    {
	    	encryptred_data[index] 		= (encryption_buffer[index] & 0b10101010) + (encryption_buffer[index + 1] & 0b01010101);
	    	encryptred_data[index + 1]	= (encryption_buffer[index] & 0b01010101) + (encryption_buffer[index + 1] & 0b10101010);
	    }

	    for(std::size_t index = 0; index < new_buffer_length; ++index)
	    {
	    	encryptred_data[index] = encryptred_data[index] ^ (key[index % (key_length / sizeof(char))] + index);
	    }

	    delete[] encryption_buffer;
	  
	    encryption_buffer = nullptr;

	    return encryptred_data;
	}

	/**
	 * @brief       Decrypts string at comple time
	 *
	 * @param       initial_string  The initial string
	 * @param       string_length   Length on the initial string 
	 * @param       key             The key for decryption
	 * @param       key_length      Length on the decryption key
	 *
	 * @return      Decrypts string
	 */
	static const char* string_decrypt(const char* initial_string, std::size_t string_length, const char* key, std::size_t key_length)
	{
		std::size_t new_buffer_length = string_length + 2 + (string_length % 2);
		int offset = 0;

		char* decryptred_data = new char[string_length];
		char* decryptred_buffer = new char[new_buffer_length]; 
		char* decryptred_mid_buffer = new char[new_buffer_length]; 

		for(std::size_t index = 0; index < new_buffer_length; ++index)
	    {
	    	decryptred_buffer[index] = initial_string[index] ^ (key[index % (key_length / sizeof(char))] + index);
	    }

	    for(std::size_t index = 0; index < new_buffer_length; index += 2)
	    {
	    	decryptred_mid_buffer[index] 		= (decryptred_buffer[index] & 0b10101010) + (decryptred_buffer[index + 1] & 0b01010101);
	    	decryptred_mid_buffer[index + 1]	= (decryptred_buffer[index] & 0b01010101) + (decryptred_buffer[index + 1] & 0b10101010);
	    }

		for(std::size_t index = 0; index <= string_length; ++index)
	    {
	    	if ((index + offset + 1) == (new_buffer_length - 1) / 2)
	    	{
	    		offset += 1;
	    	}
	    	else 
	    	{
	        	decryptred_data[index] = decryptred_mid_buffer[index + offset];
	        }
	    }

	    delete[] decryptred_buffer;
	    delete[] decryptred_mid_buffer;

	    decryptred_mid_buffer = nullptr;
	    decryptred_buffer 	  = nullptr;

	    return decryptred_data;
	}

private:
	static constexpr unsigned int  constexpr_ctoi(const char* str, int offset);
	static constexpr unsigned int  constexpr_seed();
	static constexpr std::uint32_t uniform_distribution(std::uint32_t &previous);
	static constexpr double uniform_distribution_n(std::uint32_t &previous);

protected:

	constexpr static const std::uint32_t lce_a = 4096;
	constexpr static const std::uint32_t lce_c = 150889;
	constexpr static const std::uint32_t lce_m = 714025;
};


#ifndef __CGUI_OBF_KEY__
	#define __CGUI_OBF_KEY__
#endif

#define __CGUI_OBF_GENERIC__(data, key) \
	[](){ \
		constexpr auto str_len = (__builtin_strlen(data)); \
		constexpr auto key_len = (__builtin_strlen(key)); \
		constexpr auto encrypted_data = ObfuscatedString::string_encrypt(data, str_len, key, key_len); \
		thread_local const char* obfuscated_data = ObfuscatedString::string_decrypt(encrypted_data, str_len, key, key_len); \
		return obfuscated_data; \
	}()

#define __CGUI_OBF__

#define __CGUI_OBF_S__

#endif // OBFUSCATED_STRING_HPP
